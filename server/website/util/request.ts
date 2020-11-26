import axios from 'axios'

const request = axios
const url = 'https://passwordbox.weteoes.cn'
// const url = 'http://127.0.0.1:8080'

request.interceptors.request.use((config) => {
  config.url = url + config.url
  return config
})

request.interceptors.response.use((response) => {
  return response.data
})

export default request
