type state = {price: Api.price};

let component = ReasonReact.statefulComponent "Price";

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

let make children => {
  let handleLoaded price {ReasonReact.state: state} =>
    ReasonReact.Update {price: price};
  {
    ...component,
    didMount: fun self => {
      Api.fetchBTCPrice (self.update handleLoaded);
      ReasonReact.NoUpdate
    },
    initialState: fun () => ({price: defaultPrice}: state),
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
  }
};
