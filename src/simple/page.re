type state = {price: Api.price};

let component = ReasonReact.statefulComponent "Price";

let defaultPrice: Api.price = {
  chartName: "",
  time: {updated: "", updatedISO: "", updateduk: ""}
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
      <div className="price">
        (ReasonReact.stringToElement chartName)
        
        (ReasonReact.stringToElement time.updated)
      </div>
    }
  }
};
