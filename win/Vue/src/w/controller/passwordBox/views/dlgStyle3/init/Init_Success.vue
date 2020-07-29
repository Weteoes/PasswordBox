<template>
  <div class="dlg"
       v-loading="1"></div>
</template>

<style lang="scss" scoped>
.dlg {
  width: 100%;
  height: 300px;
}
</style>

<script>
export default {
  data () {
    return {
      w: window.weteoes
    }
  },
  methods: {
    ready () {
      if (this.$parent.$data.data.optionsNow === 'local') {
        // 本地工作模式
        this.initLocal()
      } else if (this.$parent.$data.data.optionsNow === 'server') {
        // 统一身份工作模式
        this.initServer()
      } else {
        // 未知错误
        this.unknowsError()
      }
    },
    unknowsError () {
      this.showMessageBox('发生未知错误', 'error')
      this.setStepActive(1)
    },
    // 本地工作模式
    initLocal () {
      const pass = this.$parent.$data.data.pass
      if (pass === '') {
        // 未知错误
        this.unknowsError()
        return
      }
      const result = this.w.softwareApi.app('Init', 'AesInit', { pass: pass })
      if (!result) {
        this.showMessageBox('初始化数据失败', 'error')
        this.setStepActive(0, '--')
      } else {
        // 初始化完成
        this.successFun(() => {
          this.w.softwareApi.app('Init', 'ShowMainDlg')
        })
      }
    },
    // 统一身份认证登录
    initServer () {
      const isLogin = this.w.softwareApi.app('Init', 'PdSSOLogin')
      if (!isLogin) {
        this.showMessageBox('统一身份认证失败', 'error')
        this.setStepActive(1)
        return
      }
      const getServerConfig = this.w.softwareApi.app('Init', 'SSOGetServerConfig')
      // 判断是否
      if (!getServerConfig) {
        // 服务器无配置
        if (this.$parent.$data.data.pass !== '') {
          // 密码不为空说明初始化过
          this.initLocal()
          this.log('sso初始化完成')
          return
        } else {
          // 没初始化过就设置bool，Init.vue有watch事件
          this.$parent.$data.data.ServerInit = true
          return
        }
      }
      // 服务器有配置
      this.successFun(() => {
        this.w.softwareApi.app('Init', 'ShowLoginDlg')
      })
    },
    // 成功回调
    successFun (fun) {
      setTimeout(fun, 600)
    },
    setStepActive (stepActive, type) {
      if (type === undefined) this.$parent.stepActive = stepActive
      else if (type === '--') this.$parent.stepActive--
      else if (type === '++') this.$parent.stepActive++
    },
    showMessageBox (msg, type) {
      this.$parent.showMessageBox(msg, type)
    },
    log (...msg) {
      window.console.log(...msg)
    }
  },
  mounted () {
    if (this.$store.state.debug) {
      window.debug = this
    }
    this.ready()
  }
}
</script>
