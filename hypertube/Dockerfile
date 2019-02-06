FROM debian:stretch

RUN apt-get update 

# For php 7.3
RUN apt -y install wget lsb-release apt-transport-https ca-certificates
RUN wget -O /etc/apt/trusted.gpg.d/php.gpg https://packages.sury.org/php/apt.gpg
RUN echo "deb https://packages.sury.org/php/ stretch main" | tee /etc/apt/sources.list.d/php7.3.list

RUN apt-get update 

RUN apt-get install -y \
    nginx \
	php7.3-fpm \
	postgresql postgresql-client \
	curl \
	git \
	php7.3-curl \
	php7.3-xml \
	php7.3-mbstring \
	php7.3-zip \
	php7.3-sqlite \
	php7.3-bcmath \
	gnupg \
	ffmpeg libavcodec-extra libav-tools \
	rabbitmq-server \
	sudo

# For nodejs 11
RUN curl -sL https://deb.nodesource.com/setup_11.x | bash -
RUN apt-get install -y nodejs


EXPOSE 80
EXPOSE 443

EXPOSE 9091

COPY ./config/nginx /etc/nginx/sites-available/default
COPY ./config/downloader /etc/init.d/downloader

RUN chmod 715 /etc/init.d/downloader

# Install symfony

RUN curl -sS https://get.symfony.com/cli/installer | bash
RUN mv /root/.symfony/bin/symfony /usr/local/bin/symfony

# Install composer

WORKDIR /tmp
RUN curl --silent --show-error https://getcomposer.org/installer | php
RUN mv composer.phar /usr/local/bin/composer


WORKDIR /var/www

CMD ["nginx", "-g", "daemon off;"]
