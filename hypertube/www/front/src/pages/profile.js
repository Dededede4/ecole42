import React from 'react';
import langue from '../modules/langage';



const my_profilePage = ({ match }) => (
    <div>
        <h1 className="title" style={{ textAlign: 'center' }}>
      {langue.translate('my profile')}
      </h1>
    <hr />
      {/* <article className="box" style={{ width: '100%', position: 'relative' }}>
        <div className="columns">
          <div className="column">
            {langue.translate('productor') + ':'}
            <p className="subtitle">
              <b>{video.productor}</b>
            </p>
            {langue.translate('actor') + ':'}
            <p className="subtitle">
              <b>{video.actor}</b>
            </p>
            {langue.translate('date') + ':'}
            <p className="subtitle">
              <b>{video.date}</b>
            </p>
          </div>
          <div className="column">
            {langue.translate('duration') + ':'}
            <p className="subtitle">
              <b>{video.duration}</b>
            </p>
            {langue.translate('description') + ':'}
            <p className="subtitle">
              <b>{video.description}</b>
            </p>
            {langue.translate('rate') + ':'}
            <p className="subtitle">
              <b>
                <Stars rate={video.rate} />
              </b>
            </p>
          </div>
        </div>
      </article> */}
    </div>






  );

export default my_profilePage;
