let component = ReasonReact.statefulComponent "Price";

type state = {price: Api.price};

let make children => {
  let handleLoaded price {ReasonReact.state: state} =>
    ReasonReact.Update {price: price};
  {
    ...component,
    didMount: fun self => {
      Api.fetchBTCPrice (self.update handleLoaded);
      ReasonReact.NoUpdate
    },
    initialState: fun () => ({price: {chartName: "test"}}: state),
    render: fun {state} => {
      let chartName = state.price.chartName;
      <div className="price"> (ReasonReact.stringToElement chartName) </div>
    }
  }
};
