type user = {. "name": string};

type todoType = {
  .
  "id": int,
  "created_at": string,
  "title": string,
  "user": user,
};

type state = {
  .
  "todos": array(todoType),
  "loading": bool,
};

type todosGqlResp = {. "data": state};

type response = {. "data": state};

external toApolloResult: 'a => response = "%identity";

type action =
  | SetTodos(array(todoType));
[@react.component]
let make = (~client, ~latestTodoId) => {
  let (state, dispatch) =
    React.useReducer(
      (_, action) => {
        let SetTodos(todos) = action;
        {"todos": todos, "loading": false};
      },
      {"todos": [||], "loading": true},
    );
  let fetchOlderTodos = () => {
    let existingTodoLength = Array.length(state##todos);
    let lastTodoId =
      if (existingTodoLength == 0) {
        10000000;
      } else {
        state##todos[existingTodoLength - 1]##id;
      };
    let fetchOlderTodosQuery =
      GraphQLQueries.GetOlderTodos.make(~lastId=lastTodoId, ());
    let query = {
      "query": ApolloClient.gql(. fetchOlderTodosQuery##query),
      "variables": fetchOlderTodosQuery##variables,
    };
    let apolloData = client##query(query);
    apolloData
    |> Js.Promise.then_(gqlResp => {
         let resp = toApolloResult(gqlResp);
         let newTodos = Array.append(state##todos, resp##data##todos);
         dispatch(SetTodos(newTodos));
         Js.Promise.resolve();
       })
    |> ignore;
  };
  let fetchPublicTodos = () => {
    let fetchPublicTodosQuery = GraphQLQueries.GetPublicTodos.make();
    let query = {
      "query": ApolloClient.gql(. fetchPublicTodosQuery##query),
      "variables": fetchPublicTodosQuery##variables,
    };
    let apolloData = client##query(query);
    apolloData
    |> Js.Promise.then_(gqlResp => {
         let resp = toApolloResult(gqlResp);
         dispatch(SetTodos(resp##data##todos));
         Js.Promise.resolve();
       })
    |> ignore;
  };
  React.useEffect0(() => {
    fetchPublicTodos();
    None;
  });
  // let todoList = List.map(t => <FeedItem todo=t />, sampleTodos);
  let todoList =
    Array.map(
      t =>
        <FeedItem
          todo=t
          key={
            t##title;
          }
        />,
      state##todos,
    );
  let existingTodoLength = Array.length(state##todos);

  let latestVisibleId =
    if (existingTodoLength > 0) {
      state##todos[0]##id;
    } else {
      0;
    };

  let shouldShowNewTodosBanner = latestVisibleId < latestTodoId;

  let newTodosBanner =
    if (shouldShowNewTodosBanner) {
      <div className="loadMoreSection">
        {ReasonReact.string("New tasks have arrived!")}
      </div>;
    } else {
      ReasonReact.null;
    };

  let oldTodosButton = {
    <div className="loadMoreSection" onClick={_ => fetchOlderTodos()}>
      {ReasonReact.string("Load older tasks")}
    </div>;
  };

  <React.Fragment>
    {state##loading
       ? <div> {ReasonReact.string("Loading...")} </div>
       : <div className="todoListWrapper">
           newTodosBanner
           <ul> {ReasonReact.array(todoList)} </ul>
           oldTodosButton
         </div>}
  </React.Fragment>;
};