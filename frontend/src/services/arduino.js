import axios from 'axios';

const WIFI_IP = import.meta.env.VITE_WIFI_IP;
const BASE_URL = `http://${WIFI_IP}`;

const openGate = async () => {
  axios.get(`${BASE_URL}/gate`);
};

const openGarage = async () => {
  axios.get(`${BASE_URL}/garage`);
};

export default { openGate, openGarage };
