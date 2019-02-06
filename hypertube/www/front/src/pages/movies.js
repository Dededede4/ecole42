import React from 'react';
import { withRouter } from 'react-router';
import langue from '../modules/langage';
import ControlledInput from '../containers/controlledInput';
import Stars from '../components/stars';
import { callApi } from '../utils';

const searchBarStyle = {
  width: '60%',
  marginLeft: '20%',
};

const titleStyle = { marginTop: '2.5em', textAlign: 'center' };

const noData = 'https://bedekodzic.pl/wp-content/uploads/2018/05/%EF%BC%9F.png';

const MovieCard = withRouter(({ history, movie }) => (
  <div
    className="card"
    style={{ cursor: 'pointer' }}
    onClick={() => history.push(`/movie/${movie.id}`)}
  >
    <div className="card-image">
      <figure className="image">
        <img src={movie.pic || noData} alt="Placeholder" />
      </figure>
    </div>
    <div className="card-content">
      <div className="media">
        <div className="media-content">
          <p className="title is-4">{movie.title}</p>
          <p className="subtitle is-6">{movie.date}</p>
        </div>
      </div>
      <div className="content">
        <Stars rate={movie.rate} />
      </div>
    </div>
  </div>
));

const format_movies = ({ large_cover_image, title, year, rating }) => ({
  title,
  pic: large_cover_image,
  rate: rating / 2,
  date: year,
  id: 'mdr',
});

class HomePage extends React.Component {
  state = { movies: [], search: '', search_loading: false, page: 1 };

  lock = false;

  scrollcb = async () => {
    if (this.lock) return;
    if (window.scrollY + window.innerHeight + 40 >= document.getElementById('root').offsetHeight) {
      this.lock = true;
      console.log('page:', this.state.page);
      const { data } = await callApi({
        endPoint: `https://yts.am/api/v2/list_movies.json`,
        qs: {
          limit: 9,
          page: this.state.page + 1,
          ...(!!this.state.search ? { query_term: this.state.search } : {}),
          sort_by: 'year',
        },
        json: true,
      });
      if (data.movies) {
        this.state.movies.push(...data.movies.map(format_movies));
        this.setState({ movies: this.state.movies, page: this.state.page + 1 });
      }
      console.log('Hey', window.scrollY);
      this.lock = false;
    }
  };

  searchChange = e => {
    this.setState({ search: e, page: 1, search_loading: true });
    // callApi({ endpoint: `search/${e}` }).then(data => this.setState({ movies: data }));
    callApi({
      endPoint: `https://yts.am/api/v2/list_movies.json`,
      qs: {
        limit: 9,
        page: 1,
        query_term: e,
        sort_by: 'year',
        ...(!!this.state.search ? { query_term: this.state.search } : {}),
      },
      json: true,
    }).then(({ data }) =>
      this.setState({
        movies: data.movies ? data.movies.map(format_movies) : [],
        search_loading: false,
      })
    );
    // }).then(({ data }) => console.log(data.movies));
  };

  componentDidMount() {
    this.setState({ loading: true });
    window.addEventListener('scroll', this.scrollcb);
    callApi({
      endPoint: `https://yts.am/api/v2/list_movies.json`,
      qs: { limit: 9, page: this.state.page, sort_by: 'year' },
      json: true,
    }).then(({ data }) =>
      this.setState({ movies: data.movies ? data.movies.map(format_movies) : [], loading: false })
    );
  }

  componentWillUnmount() {
    window.removeEventListener('scroll', this.scrollcb);
  }

  render() {
    return (
      <div>
        <div className="field" style={searchBarStyle}>
          <div className={`control is-large ${this.state.search_loading ? 'is-loading' : ''}`}>
            <ControlledInput
              // style={searchBarStyle}
              className={`input is-large ${this.state.search_loading ? 'is-loading' : ''}`}
              className={`input is-large is-loading`}
              type="text"
              placeholder={langue.translate('search')}
              onChange={this.searchChange}
            />
          </div>
        </div>
        {this.state.loading ? (
          <p className="subtitle is-3" style={titleStyle}>
            Loading...
          </p>
        ) : !!this.state.movies.length ? (
          <div ref={elem => (this.grid = elem)} className="Movies-grid">
            {console.log(this.state.movies)}
            {this.state.movies.map((movie, index) => (
              <MovieCard key={index} movie={movie} />
            ))}
          </div>
        ) : (
          <p className="subtitle is-3" style={titleStyle}>
            {' '}
            No result!{' '}
          </p>
        )}
      </div>
    );
  }
}

export default withRouter(HomePage);
