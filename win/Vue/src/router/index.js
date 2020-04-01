import Vue from 'vue'
import VueRouter from 'vue-router'
import ControllerPasswordBox from '@/w/controller/passwordBox'
import controllerError from '@/w/controller/error'

Vue.use(VueRouter)

const routes = [
  ControllerPasswordBox.router,
  controllerError.router
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router
