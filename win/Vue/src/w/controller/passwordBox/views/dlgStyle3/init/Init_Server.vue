<template>
  <div class="dlg"
       v-loading="1"
       element-loading-text="请在弹出的窗口进行操作"></div>
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
      this.w.softwareApi.app('Init', 'ShowLogin_SSODlg')
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
