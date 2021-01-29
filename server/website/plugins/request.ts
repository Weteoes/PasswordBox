import axios from 'axios'

const request = axios
request.defaults.withCredentials = true // 跨域set-cookie

request.interceptors.request.use((config) => {
  const store = window.$nuxt.$store
  config.url = store.getters['url/apiHost'] + config.url
  return config
})

request.interceptors.response.use((response) => {
  return response.data
})

export default request
