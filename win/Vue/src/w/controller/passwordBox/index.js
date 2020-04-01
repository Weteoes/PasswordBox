import app from './App'
import ViewInit from './views/Init'
import ViewAbout from './views/About'
import ControllerError from '@/w/controller/error'

export default {
  router: {
    path: '/passwordBox/ui',
    component: app,
    children: [
      { path: '/', component: ControllerError.error404 },
      { path: 'init', component: ViewInit },
      { path: 'aa', component: ViewAbout },
      ControllerError.router
    ]
  }
}
