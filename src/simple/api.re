let apiUrl = "https://api.coindesk.com/v1/bpi/currentprice.json";

type price = {chartName: string}; /*Add rest of attributes when component is rendering properly*/

let parseBTCPrice json :price =>
  Json.Decode.{chartName: json |> field "chartName" string};

let fetchBTCPrice callback =>
  Js.Promise.(
    Bs_fetch.fetch apiUrl |> then_ Bs_fetch.Response.text |>
    then_ (
      fun text =>
        Js.Json.parseExn text |> parseBTCPrice |> (
          fun price => {
            callback price;
            resolve None
          }
        )
    )
  );
