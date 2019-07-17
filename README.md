# todo-graphql

## Run Project

```sh
npm install
npm start
# in another tab
npm run webpack
```

After you see the webpack compilation succeed (the `npm run webpack` step), open up `build/index.html` (**no server needed!**). Then modify whichever `.re` file in `src` and refresh the page to see the changes.
`npx send-introspection-query https://learn.hasura.io/graphql --headers "Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImtpZCI6Ik9FWTJSVGM1UlVOR05qSXhSRUV5TURJNFFUWXdNekZETWtReU1EQXdSVUV4UVVRM05EazFNQSJ9.eyJodHRwczovL2hhc3VyYS5pby9qd3QvY2xhaW1zIjp7IngtaGFzdXJhLWRlZmF1bHQtcm9sZSI6InVzZXIiLCJ4LWhhc3VyYS1hbGxvd2VkLXJvbGVzIjpbInVzZXIiXSwieC1oYXN1cmEtdXNlci1pZCI6ImF1dGgwfDVkMWNiZmQzMTcxZDJkMGM3ZTRlYTk4MCJ9LCJuaWNrbmFtZSI6ImFhcm1hbmQuaW5ib3giLCJuYW1lIjoiYWFybWFuZC5pbmJveEBnbWFpbC5jb20iLCJwaWN0dXJlIjoiaHR0cHM6Ly9zLmdyYXZhdGFyLmNvbS9hdmF0YXIvMzM3Zjg0YWUwYzMyYmRhNWE0ZDllY2JkMTVkMzZlYjc_cz00ODAmcj1wZyZkPWh0dHBzJTNBJTJGJTJGY2RuLmF1dGgwLmNvbSUyRmF2YXRhcnMlMkZhYS5wbmciLCJ1cGRhdGVkX2F0IjoiMjAxOS0wNy0xN1QxNToyOTowOS44NjVaIiwiaXNzIjoiaHR0cHM6Ly9ncmFwaHFsLXR1dG9yaWFscy5hdXRoMC5jb20vIiwic3ViIjoiYXV0aDB8NWQxY2JmZDMxNzFkMmQwYzdlNGVhOTgwIiwiYXVkIjoiUDM4cW5GbzFsRkFRSnJ6a3VuLS13RXpxbGpWTkdjV1ciLCJpYXQiOjE1NjMzNzczNTAsImV4cCI6MTU2MzQxMzM1MCwiYXRfaGFzaCI6IldPamZsYkpRUno5UnlFWFNtd3Ftd1EiLCJub25jZSI6IkNUQVEuQ3Q4U09WM20yR3J-N0xKNzJkMWZCUDg4azhHIn0.F2GWlY3ndEWdj-8mWyJSrMxEiDsUT3RRMalkSGjPM5E4iOcdfiy9HLzk7i9NqTPhc2fH__yMbEAzBQmMR4YvSJuyQHrfnHKcP6XtaEJVk_h1yAZSgm4MNLrckAVPzVnfUuLU8EpesyR4nz_6qhRvej3whI2_xrWZT6QqH1jLoSaG763RwsdyY2YNVNDs66eL91t6AoFrdQU0G0OeLmshE5xIcZTeTzE4lBf9tQ2PtgoH1DgMaiLPdUFxesnAjXrIyDOAmCbCiC1-jj3YRZnWtASt2eNSaDBs3MQkjKR8smqLniek6qwakIRiulfgPmU1q5rcFCEihBjuGkhADOr7mg"`
**For more elaborate ReasonReact examples**, please see https://github.com/reasonml-community/reason-react-example

## Run Project with Server

To run with the webpack development server run `npm run server` and view in the browser at http://localhost:8000. Running in this environment provides hot reloading and support for routing; just edit and save the file and the browser will automatically refresh.

Note that any hot reload on a route will fall back to the root (`/`), so `ReasonReact.Router.dangerouslyGetInitialUrl` will likely be needed alongside the `ReasonReact.Router.watchUrl` logic to handle routing correctly on hot reload refreshes or simply opening the app at a URL that is not the root.

To use a port other than 8000 set the `PORT` environment variable (`PORT=8080 npm run server`).

## Build for Production

```sh
npm run clean
npm run build
npm run webpack:production
```

This will replace the development artifact `build/Index.js` for an optimized version as well as copy `src/index.html` into `build/`. You can then deploy the contents of the `build` directory (`index.html` and `Index.js`).

If you make use of routing (via `ReasonReact.Router` or similar logic) ensure that server-side routing handles your routes or that 404's are directed back to `index.html` (which is how the dev server is set up).

**To enable dead code elimination**, change `bsconfig.json`'s `package-specs` `module` from `"commonjs"` to `"es6"`. Then re-run the above 2 commands. This will allow Webpack to remove unused code.
