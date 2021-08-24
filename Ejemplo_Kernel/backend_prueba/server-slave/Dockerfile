# Imagen Base
# En este caso es node v 14.x.x
FROM node:14 

# Asignar el workdir de la api
# workdir = en que lugar estará nuestro código
# si la ruta no existe entonces la crea
WORKDIR /usr/src/slave

# Copiar ambos archivos packege  a ./ 
# ./ -> es el WORKDIR
COPY package*.json ./

# Correr 'npm install' para instalar las dependencias que necesitamos
RUN npm install
# se pueden hacer más comando run

# Copiar todos los archivos faltantes al workdir
COPY . .

# Exponer al puerto 80 del contenedor al mundo
EXPOSE 80

# Copiar el volumen de datos de proc a /elements/procs
RUN mkdir -p /elements/procs

# Correr NodeJS
CMD [ "node", "index.js" ]
