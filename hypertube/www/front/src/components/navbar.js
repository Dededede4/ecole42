import React from 'react';
import { withState } from 'recompose';
import { withRouter } from 'react-router';
import langue from '../modules/langage';

const NavBar = ({ onLangChange, clicked, isClicked, history }) => (
  <nav
    className="navbar is-transparent"
    style={{
      boxShadow: '0 -36px 16px 0 rgba(0,0,0,0.2),0 6px 20px 0 rgba(0,0,0,0.19)',
    }}
  >
    <div className="navbar-brand">
      <div
        className="navbar-burger burger"
        data-target="langages_options"
        onClick={() => isClicked(click => !clicked)}
      >
        <span />
        <span />
        <span />
      </div>
    </div>

    <div id="langages_options" className={clicked ? 'navbar-menu is-active' : 'navbar-menu'}>
      <div className="navbar-start">
        <div
          className="navbar-item"
          style={{ cursor: 'pointer' }}
          onClick={() => history.push('/')}
        >
          <a className="navbar-item">
            <i className="fas fa-home" />
          </a>
        </div>
        <div className="navbar-item">
          <a onClick={onLangChange('francais')} className="navbar-item">
            🇫🇷
          </a>
        </div>
        <div className="navbar-item">
          <a onClick={onLangChange('english')} className="navbar-item">
            🇬🇧
          </a>
        </div>
      </div>

      <div className="navbar-end">
        <div className="navbar-item">
              <div className="buttons"></div>
              <a className="bd-tw-button button" onClick={() => history.push('/profile')}>
                  <span>{langue.translate('profile')}</span>
              </a>

              <a className="button is-danger">
                <span>{langue.translate('disconnect')}</span>
              </a>
        </div>
      </div>
    </div>
  </nav>
);

const enhance = withState('clicked', 'isClicked', false);

export default withRouter(enhance(NavBar));
