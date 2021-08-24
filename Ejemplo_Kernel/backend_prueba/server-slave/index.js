// DOTENV carga configuracion que tenemos en el archivo .env 
// en .env definir todas las variables de entorno
require('dotenv').config();

// Modulos Instalados
const express = require('express');
const axios = require('axios');

const app = new express(); // Crear una API express

const fs = require('fs'); // cargar modulo fs, para leer un archivo en este caso timestamps que esta en el proc

const { getHtmlList } = require('./templates'); // modulo cargado en template.js

// isTesting = es una variable de entorno configurarda en nuestro server de pruebas, el server no tendra esta variable, por lo tanto si leeremos el archivo proc
const isTesting = process.env.TESTING === "true";



// ********************** FUNCIONES ***********************

// getTimestamps = Función Expresada = va a ir a leer el modulo kernel timestamps y regresará la hora del sistema
const getTimestamp = () => {
    // return fs.readFileSync('/elements/procs/timestamps', 'utf-8').toString(); // TODO: lee el volumen
    return fs.readFileSync('/proc/timestamps', 'utf-8').toString(); // TODO: no se creo volumen
};

// safeGetTimestamp = funcion que sirve para devolver ya sea informaciónd el modulo si estamos en un VM o en caso contrario si estamos en una PC local la hora del sistema 
const safeGetTimestamp = () => {

    // Si no estamos en una VM, y estamos en maquina local, no podriamos ingresar al modulo por lo cual solo obtendremos otra información.
    if (isTesting) {
        const date = new Date();
        return `${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`
    }

    // Si estamos desde una VM, entonces iremos a hacer lectura del timestamps
    try {
        // Si todo es correcto, retornamo la hora del sistema
        return getTimestamp();
    } catch ({ message }) {
        // Si existe un error
        return `No se pudo leer el modulo ${message}`;
    }
};

// Habilitamos los CORS
app.all('/', (req, res, next) => {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Header", "X-Requested-With");
    next();
});

// IMPORTANTE = le decimos a express que necesitamos trabajar con intercambio de datos en formato json
app.use(express.json({ extended: true }));



// petición get a express al directorio raiz, genera un html y muestra un mensaje
app.get('/', async(req, res) => { // es importante notar que este es un metodo async, ya que utilizamos await dentro de el

    // Intentamos realizar el get al otro servidor
    try {
        // getHtmlList = genera una lista
        const html = getHtmlList([{
            name: "Rafael",
            msg: "SO1",
            timestamp: safeGetTimestamp()
        }]); // Obtenemos la lista con un formato de lista de HTML

        console.log("Server1: Devolviendo HTML");

        return res.send(html); // Devolvemos el HTML para que sea renderizado por el navegador

    } catch (error) {
        console.log(`Server1: Error en la peticion, error: ${error.message}`);
        return res.status(500).send({ msg: error.message }); // Existio un error, devuelve el mensaje del error
    }
});

// Configuración del puerto
const PORT = process.env.port || 4000;

// Iniciar API
app.listen(PORT, () => {
    console.log(`API lista en -> http://localhost:${PORT}`);
});