<template>
  <div class="dlg_form">
    <el-steps :active="stepActive"
              align-center>
      <el-step v-for="(step, index) in steps"
               :key="index"
               :title="step"
               @click.native="stepsClick(index + 1)"></el-step>
    </el-steps>
    <div class="stepData">
      <componentsOperatingOptions v-if="stepActive == 1"></componentsOperatingOptions>
      <componentsLocal v-if="stepActive == 2 && data.optionsNow == 'local'"></componentsLocal>
      <componentsServer v-if="stepActive == 2 && data.optionsNow == 'server'"></componentsServer>
      <componentsSuccess v-if="stepActive == 3"></componentsSuccess>
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
      stepActive: 1, // 当前步骤
      steps: ['选择工作模式', '设置初始密码', '初始化'],
      element: {
        messageBox: null // 记录messagebox
      },
      // 步骤完成后同步到父级
      data: {
        optionsNow: '',
        pass: ''
      }
    }
  },
  methods: {
    ready () {
      this.$parent.dlgStyle = this.dlgStyle // 样式
      this.$parent.dlgTitle = this.dlgTitle // 标题
      this.$parent.$parent.readyCEFSize({ w: 800, div: '.dlg2_a' }) // 设置窗口大小
      this.w.softwareFun.addDlgMouseEvent(document.querySelector('.dlg2_aaa')) // 拖动条
      this.readySoftwareDlgCallBack()
    },
    // 软件窗口回调
    readySoftwareDlgCallBack () {
      const that = this
      this.w.readySoftwareDlgCallBack.init = {
        nextStepActive () {
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
        this.$data.steps[1] = '设置初始密码'
      } else if (value === 'server') {
        this.$data.steps[1] = '统一身份认证'
      } else {
        this.$data.steps[1] = '设置初始密码'
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
