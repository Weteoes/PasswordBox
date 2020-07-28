<template>
  <div class="dlg"
       @keydown="dlgKeyDown">
    <div class="title">请设置一个安全密码</div>
    <div class="title1">安全密码丢失将无法再次解锁数据</div>
    <div class="data">
      <div class="onlyData">
        <el-input placeholder="请输入安全密码"
                  v-model="userInput.pass0"
                  show-password></el-input>
      </div>
      <div class="onlyData">
        <el-input placeholder="请输入安全密码"
                  v-model="userInput.pass1"
                  show-password></el-input>
      </div>
      <div class="onlyData">
        <el-button id="nextButton"
                   @click="nextButtonClick"
                   type="primary">下一步</el-button>
      </div>
    </div>
  </div>
</template>

<style lang="scss" scoped>
.dlg {
  width: 300px;
  margin: 25px auto;
}

.dlg > .title {
  height: 20px;
  font-size: 15px;
  margin-bottom: 3px;
}

.dlg > .title1 {
  height: 20px;
  color: rgb(252, 63, 79);
  font-size: 13px;
  margin-bottom: 10px;
}

.data > .onlyData {
  padding: 10px 0;
}

.dataSelect {
  width: 100%;
}

#nextButton {
  width: 100%;
  margin-top: 30px;
}
</style>

<script>
export default {
  data () {
    return {
      w: window.weteoes,
      userInput: {
        pass0: '',
        pass1: ''
      }
    }
  },
  methods: {
    ready () {
      this.readyData()
    },
    nextButtonClick () {
      const pass0 = this.userInput.pass0
      const pass1 = this.userInput.pass1
      if (pass0 === '' || pass1 === '') {
        this.showMessageBox('请输入安全密码', 'error')
        return
      } else if (pass0.length < 6) {
        this.showMessageBox('安全密码长度不能低于6位', 'error')
        return
      } else if (pass0 !== pass1) {
        this.showMessageBox('二次确认不一致,请重新输入', 'error')
        return
      }
      this.synchronize()
      this.$parent.stepActive++
    },
    readyData () {
      this.userInput.pass0 = this.$parent.$data.data.pass
      this.userInput.pass1 = this.$parent.$data.data.pass
    },
    synchronize () {
      this.$parent.$data.data.pass = this.userInput.pass0
    },
    dlgKeyDown: function (a) {
      if (a.keyCode === 13) {
        this.nextButtonClick()
      }
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
