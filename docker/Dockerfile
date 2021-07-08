FROM ubuntu:latest
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
RUN ln -snf /usr/share/zoneinfo/${TZ} /etc/localtime && echo ${TZ} > /etc/timezone
RUN apt-get update &&\
    apt-get install --yes libboost-all-dev \
        build-essential \
        git \
        vim
