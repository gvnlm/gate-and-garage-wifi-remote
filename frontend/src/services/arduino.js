import axios from 'axios';

const PROXY_SERVER_IP = import.meta.env.VITE_PROXY_SERVER_IP;
const PROXY_SERVER_PORT = import.meta.env.VITE_PROXY_SERVER_PORT;
const BASE_URL = `http://${PROXY_SERVER_IP}:${PROXY_SERVER_PORT}`;

const openGate = async () => {
  try {
    await axios.get(`${BASE_URL}/gate`);
  } catch (error) {
    if (error.code === 'ERR_NETWORK') {
      console.log(
        `Failed to open gate: Proxy server could not be reached. Ensure it is running and the request is to the correct IP.`
      );
    } else if (error.status === 503) {
      console.log('Failed to open gate: Proxy server could not reach Arduino server');
    } else {
      console.log('Failed to open gate:', error);
    }
  }
};

const openGarage = async () => {
  try {
    await axios.get(`${BASE_URL}/garage`);
  } catch (error) {
    if (error.code === 'ERR_NETWORK') {
      console.log(
        `Failed to open garage: Proxy server could not be reached. Ensure it is running and the request is to the correct IP.`
      );
    } else if (error.status === 503) {
      console.log('Failed to open garage: Proxy server could not reach Arduino server');
    } else {
      console.log('Failed to open garage:', error);
    }
  }
};

export default { openGate, openGarage };
