FROM jupyter/base-notebook
 
USER root
RUN apt-get update
RUN apt-get install -y build-essential g++ libgl1-mesa-glx libx11-6
RUN conda install matplotlib scipy  
RUN pip install cvxopt 
COPY . /src 
WORKDIR /src

