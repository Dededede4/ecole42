import React from 'react';
import { debounce } from 'lodash';

const ControlledInput = props => {
  const debounced = debounce(e => props.onChange(e), 1000);
  const cb = e => {
    debounced(e.target.value);
  };
  return <input {...props} onChange={cb} />;
};

export default ControlledInput;
