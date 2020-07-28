import app from './App'
import dlgStyle1 from './DlgStyle1'
import dlgStyle2 from './DlgStyle2'
import dlgStyle3 from './DlgStyle3'
import viewLogin from './views/dlgStyle1/Login'
import viewChangePassword from './views/dlgStyle1/ChangePassword'
import viewMain from './views/dlgStyle2/Main'
import viewInit from './views/dlgStyle3/Init'
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
      {
        path: '3',
        component: dlgStyle3,
        children: [
          { path: 'init', component: viewInit }
        ]
      },
      controllerError.router
    ]
  }
}
