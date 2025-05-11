require('dotenv').config();
const ARDUINO_IP = process.env.ARDUINO_IP;

const express = require('express');
const morgan = require('morgan');
const { exec } = require('child_process');

const app = express();

app.use(morgan('tiny'));

// Uses `curl` to send HTTP requests to the local Arduino server since axios, fetch, and got all
// could not reach the Arduino server. I suspect it may have something to do with Node.js, since the
// exact same axios/fetch/got requests work fine when from a browser. This is a temporary solution
// until I can resolve this issue.

app.get('/gate', (req, res) => {
  exec(`curl -s http://${ARDUINO_IP}/gate`, (error) => {
    if (error) {
      console.error(error.message);
      res.status(503).json({ error: 'Arduino server could not be reached' });
    } else {
      res.status(204).end();
    }
  });
});

app.get('/garage', (req, res) => {
  exec(`curl -s http://${ARDUINO_IP}/garage`, (error) => {
    if (error) {
      console.error(error.message);
      res.status(503).json({ error: 'Arduino server could not be reached' });
    } else {
      res.status(204).end();
    }
  });
});

const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
