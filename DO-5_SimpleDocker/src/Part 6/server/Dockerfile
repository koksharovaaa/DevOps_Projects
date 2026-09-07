FROM nginx:latest

USER root

WORKDIR /server/

RUN apt-get update \
    && apt-get install -y gcc libfcgi-dev spawn-fcgi curl \
    && rm -rf /var/lib/apt/lists \
    && chown -R nginx:nginx /etc/nginx/nginx.conf \
    && chown -R nginx:nginx /var/cache/nginx \
    && chown -R nginx:nginx /server\
    && touch /var/run/nginx.pid \
    && chown -R nginx:nginx /var/run/nginx.pid \
    && chmod u-s /usr/bin/gpasswd \
    && chmod u-s /usr/bin/chsh \
    && chmod u-s /usr/bin/chfn \
    && chmod u-s /usr/bin/umount \
    && chmod u-s /usr/bin/mount \
    && chmod u-s /usr/bin/newgrp \
    && chmod u-s /usr/bin/passwd \
    && chmod u-s /usr/bin/su\
    && chmod g-s /usr/bin/chage \
    && chmod g-s /usr/sbin/unix_chkpwd \
    && chmod g-s /usr/bin/expiry

COPY ./file.c /server/
COPY ./nginx/nginx.conf /etc/nginx/

RUN gcc -o file.fcgi file.c -lfcgi

USER nginx

CMD spawn-fcgi -p 8080/server/file.fcgi && nginx -g 'daemon off;'

HEALTHCHECK --interval=30s --start-period-3s--timeout=3s CMD curl -f https://localhost:81 || exit