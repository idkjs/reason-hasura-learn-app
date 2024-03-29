type state = {text: string};

type action =
  | HandleTextChange(string);

[@react.component]
let make = (~isPublic: bool) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) => {
        let HandleTextChange(text) = action;
        {text: text};
      },
      {text: ""},
    );
  let insertTodoMutation =
    GraphQLQueries.InsertMyTodo.make(~todo=state.text, ~isPublic, ());
  <GraphQLQueries.InsertMyTodoMutation>
    ...{(mutate, _) =>
      <form
        className="formInput"
        onSubmit={event => {
          ReactEvent.Form.preventDefault(event);
          mutate(
            ~variables=insertTodoMutation##variables,
            ~refetchQueries=[|"getMyTodos"|],
            (),
          )
          |> Js.Promise.then_(data => {
               dispatch(HandleTextChange(""));
               Js.Promise.resolve();
             })
          |> ignore;
        }}>
        <input
          className="input"
          placeholder="What needs to be done?"
          value={state.text}
          onChange={event =>
            dispatch(HandleTextChange(ReactEvent.Form.target(event)##value))
          }
        />
        <i className="inputMarker fa fa-angle-right" />
      </form>
    }
  </GraphQLQueries.InsertMyTodoMutation>;
};