import error404 from './views/404'

export default {
  router: {
    path: '*',
    component: error404
  },
  error404: error404
}
