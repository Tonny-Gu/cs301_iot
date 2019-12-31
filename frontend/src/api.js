import axios from 'axios';
import getUnixTime from 'date-fns/getUnixTime';
// import subHours from 'date-fns/subHours';

const endpoint = '/api';
// const endpoint = 'http://192.168.43.189:1235/api';

async function getWorkingMode() {
  return axios.get(endpoint + '/control/mode');
}

async function changeWorkingMode(mode) {
  return axios.put(endpoint + '/control/mode', { mode });
}

async function toggleLight(id, on) {
  return axios.put(endpoint + `/control/light/${id}`, { on });
}

async function getLightHistory(from, to, interval) {
  const resp = await axios.get(endpoint + '/query/illuminance', {
    params: {
      from: getUnixTime(from),
      to: getUnixTime(to),
      interval
    }
  });
  if (resp.status != 200) throw "failed";
  return resp.data;
}

async function updateRGB(values) {
  return axios.put(endpoint + '/control/rgb', values);
}

async function getRGB() {
  const resp = await axios.get(endpoint + '/query/rgb');
  if (resp.status != 200) throw "failed";
  return resp.data;
}

async function getLatestIlluminance() {
  const resp = await axios.get(endpoint + '/query/latest_lux');
  return resp.data;
}

// async function getLatestIlluminance() {
//   const now = new Date();
//   const resp = await axios.get(endpoint + '/query/illuminance', {
//     params: {
//       from: getUnixTime(subHours(now, 2)),
//       to: getUnixTime(now),
//       interval: 3600
//     }
//   });
//   if (resp.data.length > 0) return resp.data[0];
//   else throw "failed";
// }

export default {
  getWorkingMode,
  changeWorkingMode,
  toggleLight,
  getLightHistory,
  getLatestIlluminance,
  updateRGB,
  getRGB,
};
