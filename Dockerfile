FROM node

ENV NPM_CONFIG_PREFIX /.npm-global
ENV PATH /.npm-global/bin:$PATH

RUN npm install -g particle-cli

COPY . /code
WORKDIR /code
