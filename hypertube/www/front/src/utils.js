import request from 'request-promise';

// const API_URL = 'http://localhost:4242';

export const callApi = options => {
  console.log('calling:', options);
  // options.uri = API_URL + options.endPoint;
  options.uri = options.endPoint;
  return request(options) /*.catc0h(e => console.error(e.message))*/;
};
