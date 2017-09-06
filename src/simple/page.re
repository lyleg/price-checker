type state = {price: Api.price};

let defaultCountry: Api.countryObj = {
  code: "",
  description: "",
  rate: "",
  rate_float: 0.0,
  symbol: ""
};

let defaultPrice: Api.price = {
  chartName: "",
  time: {updated: "", updatedISO: "", updateduk: ""},
  bpi: {eur: defaultCountry, usd: defaultCountry, gbp: defaultCountry}
};

type action =
  | DataLoaded Api.price;

let component = ReasonReact.reducerComponent "Price";

let make _children => {
  ...component,
  initialState: fun () => ({price: defaultPrice}: state),
  reducer: fun action _state =>
    switch action {
    | DataLoaded data => ReasonReact.Update {price: data}
    },
  didMount: fun self => {
    Api.fetchBTCPrice (self.reduce (fun data => DataLoaded data));
    ReasonReact.NoUpdate
  },
  render: fun {state} => {
    let chartName = state.price.chartName;
    let time = state.price.time;
    let rate = state.price.bpi.usd.rate;
    <div className="price">
      (ReasonReact.stringToElement chartName)
      (ReasonReact.stringToElement time.updated)
      (ReasonReact.stringToElement rate)
    </div>
  }
};
