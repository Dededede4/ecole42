import React from 'react';
import { withState } from 'recompose';

const isCheckdedbuild = onclick => (rate, mousepose, num) => {
  if (!onclick || mousepose === 0) return rate >= num;
  return mousepose >= num;
};

const Stars = ({ rate, onClick, mousepose, setMousepose }) => {
  const mouseEnter = num => () => {
    if (!onClick) return;
    setMousepose(pose => num);
  };
  const mouseLeave = num => () => {
    if (!onClick) return;
    setMousepose(pose => 0);
  };
  const onChange = num => (onClick ? _ => onClick(num) : null);
  const isCheckded = isCheckdedbuild(onClick);
  return (
    <span>
      <span
        style={!!onClick ? { cursor: 'pointer' } : {}}
        onClick={onChange(1) || (() => {})}
        onMouseEnter={mouseEnter(1)}
        onMouseLeave={mouseLeave(1)}
        className={isCheckded(rate, mousepose, 1) ? 'fa fa-star checked' : 'fa fa-star'}
      />
      <span
        style={!!onClick ? { cursor: 'pointer' } : {}}
        onClick={onChange(2) || (() => {})}
        onMouseEnter={mouseEnter(2)}
        onMouseLeave={mouseLeave(2)}
        className={isCheckded(rate, mousepose, 2) ? 'fa fa-star checked' : 'fa fa-star'}
      />
      <span
        style={!!onClick ? { cursor: 'pointer' } : {}}
        onClick={onChange(3) || (() => {})}
        onMouseEnter={mouseEnter(3)}
        onMouseLeave={mouseLeave(3)}
        className={isCheckded(rate, mousepose, 3) ? 'fa fa-star checked' : 'fa fa-star'}
      />
      <span
        style={!!onClick ? { cursor: 'pointer' } : {}}
        onClick={onChange(4) || (() => {})}
        onMouseEnter={mouseEnter(4)}
        onMouseLeave={mouseLeave(4)}
        className={isCheckded(rate, mousepose, 4) ? 'fa fa-star checked' : 'fa fa-star'}
      />
      <span
        style={!!onClick ? { cursor: 'pointer' } : {}}
        onClick={onChange(5) || (() => {})}
        onMouseEnter={mouseEnter(5)}
        onMouseLeave={mouseLeave(5)}
        className={isCheckded(rate, mousepose, 5) ? 'fa fa-star checked' : 'fa fa-star'}
      />
    </span>
  );
};

const enhance = withState('mousepose', 'setMousepose', 0);

export default enhance(Stars);
