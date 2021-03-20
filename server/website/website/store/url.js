export const state = () => ({
  // apiHost: 'http://127.0.0.1:8080',
  apiHost: 'https://passwordbox.weteoes.cn',
  ssoHost: 'https://sso.weteoes.cn', // 只有注册使用到
  ssoLoginUrl: '/sso/redirect?url=', // 登录先跳到后台，再由后台跳到sso
  ssoSignOutUrl: '/sso/logout?url=',
  ssoRegisteredUrl: '/Registered/byMail/?callback=',
})

export const getters = {
  apiHost(state) {
    return state.apiHost
  },
  ssoLoginUrl(state) {
    return state.apiHost + state.ssoLoginUrl
  },
  ssoSignOutUrl(state) {
    return state.apiHost + state.ssoSignOutUrl
  },
  ssoRegisteredUrl(state) {
    return state.ssoHost + state.ssoRegisteredUrl
  },
}

export const mutations = {}
