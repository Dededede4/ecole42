all: build run

build:
	docker build --tag=hyperteub .

install:
	rm -f /var/www/var/cache/
	make build
	make run
	docker exec hypertueub bash -c "cd /var/www/ && composer install --ignore-platform-reqs"
	docker exec hypertueub bash -c "cd /var/www/downloadeur/ && npm i"
	docker exec hypertueub bash -c "cd /var/www/front && npm i && npm run build &&  node html_to_twig /var/www/front/build/index.html > /var/www/templates/base.html.twig && rm -rf /var/www/public/react &&  mv /var/www/front/build /var/www/public/react ;"
	docker exec hypertueub php /var/www/bin/console doctrine:database:create
	docker exec hypertueub bash -c "cd /var/www/ && php bin/console doctrine:schema:update --force"
	make exec
	docker exec hypertueub chmod 666 /tmp/bdd.sqlite
	rm -rf /var/www/var/cache/

run:
	docker run -d --name hypertueub -p 4242:80 -v $(CURDIR)/www:/var/www hyperteub

exec:
	docker exec hypertueub /etc/init.d/php7.3-fpm start
	docker exec hypertueub service rabbitmq-server start
	docker exec hypertueub service downloader start

clean:
	-docker kill hypertueub
	-docker rm hypertueub

re: clean all

bash:
	docker exec -i -t hypertueub /bin/bash
