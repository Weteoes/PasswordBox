import app from './App'
import dlgStyle1 from './DlgStyle1'
import dlgStyle2 from './DlgStyle2'
import viewInit from './views/DlgStyle1/Init'
import viewLogin from './views/DlgStyle1/Login'
import viewChangePassword from './views/DlgStyle1/ChangePassword'
import viewMain from './views/DlgStyle2/Main'
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
          { path: 'init', component: viewInit },
          { path: 'login', component: viewLogin },
          { path: 'changePassword', component: viewChangePassword }
        ]
      },
      {
        path: '2',
        component: dlgStyle2,
        children: [
          { path: 'main', component: viewMain }
        ]
      },
      controllerError.router
    ]
  }
}
