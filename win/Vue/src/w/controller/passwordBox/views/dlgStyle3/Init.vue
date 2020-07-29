<template>
  <div class="dlg_form">
    <el-steps :active="stepActive"
              align-center>
      <el-step v-for="(step, index) in steps"
               :key="index"
               :title="step.title"
               @click.native="stepsClick(index + 1)"></el-step>
    </el-steps>
    <div class="stepData">
      <componentsOperatingOptions v-if="stepActive == 1"></componentsOperatingOptions>
      <componentsServer v-if="stepActive == 2 && data.optionsNow == 'server'"></componentsServer>
      <componentsLocal v-if="!data.ServerInit && stepActive == 2 && data.optionsNow == 'local'"></componentsLocal>
      <componentsLocal v-if="data.ServerInit && stepActive == 3 && data.optionsNow == 'server'"></componentsLocal>
      <componentsSuccess v-if="!data.ServerInit && stepActive == 3"></componentsSuccess>
      <componentsSuccess v-if="data.ServerInit && stepActive == 4"></componentsSuccess>
    </div>
  </div>
</template>

<style lang="scss" scoped>
.dlg_form {
  width: 90%;
  margin: 30px auto;
}
.dlg_form > .title {
  height: 20px;
  font-size: 15px;
  margin-bottom: 3px;
}

.dlg_form > .title1 {
  height: 20px;
  color: rgb(252, 63, 79);
  font-size: 13px;
  margin-bottom: 10px;
}

.data > .onlyData {
  padding: 10px 0;
}

.stepData {
  height: 300px;
  padding: 10px;
}
</style>

<script>
import componentsOperatingOptions from './init/Init_OperatingOptions'
import componentsLocal from './init/Init_Local'
import componentsServer from './init/Init_Server'
import componentsSuccess from './init/Init_Success'

export default {
  data () {
    return {
      w: window.weteoes,
      dlgTitle: '密码保管箱',
      dlgStyle: 'width: 800px', // 需要和readyCEFSize一起修改
      stepActive: -1, // 当前步骤（1开始）
      steps: [],
      element: {
        messageBox: null // 记录messagebox
      },
      // 步骤完成后同步到父级
      data: {
        optionsNow: '',
        pass: '',
        ServerInit: false // SSO登录后服务器无配置时需要初始化
      }
    }
  },
  methods: {
    ready () {
      this.$parent.dlgStyle = this.dlgStyle // 样式
      this.$parent.dlgTitle = this.dlgTitle // 标题
      this.readySoftwareDlgCallBack()
      this.readyData()
      this.$parent.$parent.readyCEFSize({ w: 800, h: 480, div: '.dlg2_a' }) // 设置窗口大小
      this.w.softwareFun.addDlgMouseEvent(document.querySelector('.dlg2_aaa')) // 拖动条
    },
    readyData () {
      // 默认步骤
      this.setSteps().local()
      // 初始化步骤为第一个
      this.stepActive = 1
      // 初始化子数据
      this.data.optionsNow = ''
      this.data.pass = ''
      this.data.ServerInit = false
    },
    // 软件窗口回调
    readySoftwareDlgCallBack () {
      const that = this
      this.w.softwareDlgCallBack.init = {
        nextStepActive (hasConfig) {
          that.$data.stepActive++
        }
      }
    },
    // 步骤点击事件
    stepsClick (stepActive) {
      // stepActive 1代表第一个
      // 只可以后退(且不为最后一个)
      const now = this.$data.stepActive
      if (now > stepActive && now !== this.$data.steps.length) {
        this.$data.stepActive = stepActive
      }
    },
    setSteps () {
      const that = this
      return {
        local () {
          that.steps = [
            { title: '选择工作模式' },
            { title: '设置初始密码' },
            { title: '初始化' }
          ]
        },
        server () {
          that.steps = [
            { title: '选择工作模式' },
            { title: '统一身份认证' },
            { title: '初始化' }
          ]
        },
        serverNotInit () {
          that.steps = [
            { title: '选择工作模式' },
            { title: '统一身份认证' },
            { title: '设置初始密码' },
            { title: '初始化' }
          ]
        }
      }
    },
    showMessageBox (msg, type) {
      if (this.element.messageBox !== null) {
        this.element.messageBox.close()
      }
      this.element.messageBox = this.$message({
        showClose: true,
        message: msg,
        type: type
      })
    },
    log (...msg) {
      window.console.log(...msg)
    }
  },
  mounted () {
    this.ready()
  },
  watch: {
    'data.optionsNow': function (value, oldValue) {
      if (value === 'local') {
        this.setSteps().local() // 默认步骤
      } else if (value === 'server') {
        this.setSteps().server() // SSO
      } else {
        this.setSteps().local() // 默认步骤
      }
    },
    'data.ServerInit': function (value, oldValue) {
      this.setSteps().serverNotInit() // SSO没初始化过
    },
    stepActive: function (value, oldValue) {
      if (value === 1) {
        // 如果是第一个步骤，重新初始化
        this.readyData()
      }
    }
  },
  components: {
    componentsOperatingOptions,
    componentsLocal,
    componentsServer,
    componentsSuccess
  }
}
</script>
