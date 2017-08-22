let apiUrl = "https://api.coindesk.com/v1/bpi/currentprice.json";

type timeObj = {
  updated: string,
  updatedISO: string,
  updateduk: string
};

type price = {
  chartName: string,
  time: timeObj
};

let parseTimeObj json :timeObj =>
  Json.Decode.{
    updated: json |> field "updated" string,
    updatedISO: json |> field "updatedISO" string,
    updateduk: json |> field "updateduk" string
  };

let parseBTCPrice json :price =>
  Json.Decode.{
    chartName: json |> field "chartName" string,
    time: json |> field "time" parseTimeObj
  };

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
