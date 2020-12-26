export const state = () => ({
  // ssoHost: 'http://127.0.0.1:8080',
  ssoHost: 'https://passwordbox.weteoes.cn',
  ssoLoginUrl: '/sso/redirect?url=',
  ssoSignOutUrl: '/sso/logout?url=',
})

export const getters = {
  ssoLoginUrl(state) {
    return state.ssoHost + state.ssoLoginUrl
  },
  ssoSignOutUrl(state) {
    return state.ssoHost + state.ssoSignOutUrl
  },
}

export const mutations = {}
