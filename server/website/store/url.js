export const state = () => ({
  // apiHost: 'http://127.0.0.1:8080',
  apiHost: 'https://passwordbox.weteoes.cn',
  ssoHost: 'https://sso.weteoes.cn/', // 只有注册使用到
  ssoLoginUrl: '/sso/redirect?url=',
  ssoSignOutUrl: '/sso/logout?url=',
  ssoRegisteredUrl: '/Registered/byMail/?callback=',
})

export const getters = {
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
