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
        const pass = this.$parent.$data.data.pass
        if (pass === '') {
          // 未知错误
          this.unknowsError()
          return
        }
        this.initLocal(pass)
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
    initLocal (pass) {
      const result = this.w.softwareApi.app('Init', 'AesInit', { pass: pass })
      if (!result) {
        this.showMessageBox('初始化数据失败', 'error')
        // this.setStepActive(2)
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
      this.successFun(() => {
        this.w.softwareApi.app('Init', 'ShowLoginDlg')
      })
    },
    // 成功回调
    successFun (fun) {
      setTimeout(fun, 600)
    },
    setStepActive (stepActive) {
      this.$parent.stepActive = stepActive
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
