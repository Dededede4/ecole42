import React from 'react';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
import './App.css';
import NavBar from './components/navbar.js';
import langue from './modules/langage';
import Home from './pages/home';
import Movie from './pages/movie';
import Movies from './pages/movies';
import Profile from './pages/profile';

const About = () => <h1>About</h1>;
const Users = () => <h1>Users</h1>;

const Forsansfor = () => <h1>404</h1>;

class App extends React.Component {
  state = {
    langue: langue.lang,
  };

  changeLangage = new_lang => e => {
    if (langue.change_langage(new_lang)) this.setState({ langue: new_lang });
  };

  render() {
    return (
      <Router>
        <div>
          <NavBar onLangChange={this.changeLangage} />
          <section className="section">
            <div className="container">
              <Switch>
                <Route path="/" exact component={Home} />
                <Route path="/movies/" component={Movies} />
                <Route path="/movie/:id" component={Movie} />
                <Route path="/about/" component={About} />
                <Route path="/users/" component={Users} />
                <Route path="/profile/" component={Profile} />
                <Route component={Forsansfor} />
              </Switch>
            </div>
          </section>
        </div>
      </Router>
    );
  }
}

export default App;
