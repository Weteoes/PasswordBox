export default {
  // Target (https://go.nuxtjs.dev/config-target)
  target: 'static',

  // Global page headers (https://go.nuxtjs.dev/config-head)
  head: {
    titleTemplate: '%s',
    meta: [
      { charset: 'utf-8' },
      {
        name: 'viewport',
        content:
          'width=device-width, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0, user-scalable=no',
      },
      {
        hid: 'description',
        name: 'description',
        content:
          '密码保管箱，通过不可逆加密模式保护您的账号密码安全，强密码解决方案。免费使用，不限数量的网站账户信息记录。数据支持云同步，支持主流浏览器。AES 256 加密算法，在遗失密码的情况下数据将无法被再次解密。',
      },
    ],
    link: [{ rel: 'icon', type: 'image/x-icon', href: '/favicon.ico' }],
  },

  // Global CSS (https://go.nuxtjs.dev/config-css)
  css: ['ant-design-vue/dist/antd.css'],

  // Plugins to run before rendering page (https://go.nuxtjs.dev/config-plugins)
  plugins: ['@/plugins/antd-ui', '@/plugins/scripts'],

  // Auto import components (https://go.nuxtjs.dev/config-components)
  components: true,

  // Modules for dev and build (recommended) (https://go.nuxtjs.dev/config-modules)
  buildModules: [
    // https://go.nuxtjs.dev/typescript
    '@nuxt/typescript-build',
  ],

  // Modules (https://go.nuxtjs.dev/config-modules)
  modules: [
    // https://go.nuxtjs.dev/axios
    // '@nuxtjs/axios',
    '@nuxtjs/style-resources',
  ],
  styleResources: {
    less: ['@/assets/styles/variable.less', '@/assets/styles/app.less'],
  },
  // Axios module configuration (https://go.nuxtjs.dev/config-axios)
  axios: {},

  // Build Configuration (https://go.nuxtjs.dev/config-build)
  build: {
    publicPath: '/_w/',
    extractCSS: true,
  },
  // 404
  generate: {
    fallback: true,
    mode: 'spa',
    interval: 150,
  },
  // router: {
  //   extendRoutes(routes, resolve) {
  //     // routes.push({
  //     //   path: '*',
  //     //   component: resolve('./layouts/error1.vue'),
  //     // })
  //     console.log(routes)
  //   },
  // },
}
