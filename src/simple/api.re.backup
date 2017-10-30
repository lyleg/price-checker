let apiUrl = "https://api.coindesk.com/v1/bpi/currentprice.json";

type timeObj = {
  updated: string,
  updatedISO: string,
  updateduk: string
};

type countryObj = {
  code: string,
  description: string,
  rate: string,
  rate_float: float,
  symbol: string
};

type bpiObj = {
  usd: countryObj,
  eur: countryObj,
  gbp: countryObj
};

type price = {
  chartName: string,
  time: timeObj,
  bpi: bpiObj
};

let parseCountry json :countryObj =>
  Json.Decode.{
    code: json |> field "code" string,
    description: json |> field "description" string,
    rate: json |> field "rate" string,
    rate_float: json |> field "rate_float" float,
    symbol: json |> field "symbol" string
  };

let parseBPIObj json :bpiObj =>
  Json.Decode.{
    eur: json |> field "EUR" parseCountry,
    usd: json |> field "USD" parseCountry,
    gbp: json |> field "GBP" parseCountry
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
    time: json |> field "time" parseTimeObj,
    bpi: json |> field "bpi" parseBPIObj
  };

let fetchBTCPrice callback=>
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
