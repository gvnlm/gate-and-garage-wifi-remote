import axios from 'axios';

const WIFI_IP = import.meta.env.VITE_WIFI_IP;
const BASE_URL = `http://${WIFI_IP}`;

const openGate = async () => {
  try {
    await axios.get(`${BASE_URL}/gate`);
  } catch (error) {
    if (error.code === 'ERR_NETWORK') {
      console.log(
        `Failed to open gate: Arduino server could not be reached. Ensure it is running and the request is to the correct IP.`
      );
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
        `Failed to open gate: Arduino server could not be reached. Ensure it is running and the request is to the correct IP.`
      );
    } else {
      console.log('Failed to open gate:', error);
    }
  }
};

export default { openGate, openGarage };
