import app from './App'
import dlgStyle1 from './DlgStyle1'
import viewInit from './views/Init'
import controllerError from '@/w/controller/error'

export default {
  router: {
    path: '/passwordBox/ui',
    component: app,
    children: [
      {
        path: '1',
        component: dlgStyle1,
        children: [
          { path: 'init', component: viewInit }
        ]
      },
      controllerError.router
    ]
  }
}
