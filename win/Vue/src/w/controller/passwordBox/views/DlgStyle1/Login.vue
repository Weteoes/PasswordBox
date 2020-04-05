<template>
  <div class="dlg_form">
    <div class="title">请输入安全密码</div>
    <div class="userInputAll">
      <div class="userInputOnly">
        <input class="userInput" v-model="userInput.pass" placeholder="请输入安全密码" type="password" />
      </div>
    </div>
    <div class="errorMsg" style="height: 16px" v-text="errorMsg"></div>
    <div class="userButton">
      <div class="userButtonOnly">
        <div class="only" @click="buttonNext">确定</div>
      </div>
    </div>
  </div>
</template>

<style lang="scss" scoped>
.dlg_form > .title {
  font-size: 14px;
  margin-bottom: 3px;
}
.dlg_form > .errorMsg {
  color: rgb(252, 63, 79);
  font-size: 12px;
}
.userInputAll {
  margin: 5px 0;
}
.userInputOnly {
  display: flex;
}
.userInput {
  width: 100%;
  height: 24px;
  border: 1px solid #9c9c9c;
  margin: 5px auto;
  font-size: 14px;
  padding: 2px 5px;
  outline: none;
}
.userButton {
  display: flex;
  margin: 5px auto 5px auto;
}
.userButtonOnly {
  height: 30px;
  flex: 1;
}
.userButtonOnly > .only {
  height: 30px;
  line-height: 30px;
  border-radius: 6px;
  background: #31acff;
  text-align: center;
  color: #fff;
  font-size: 15px;
  cursor: pointer;
}
.userButtonOnly > .only:hover {
  background: #189df5;
}
</style>

<script>
export default {
  data () {
    return {
      w: window.weteoes,
      userInput: {
        pass: ''
      },
      dlgTitle: '登录',
      dlgStyle: 'width: 350px',
      errorMsg: ''
    }
  },
  methods: {
    ready () {
      this.$parent.dlgStyle = this.dlgStyle // 样式
      this.$parent.dlgTitle = this.dlgTitle // 标题
      this.w.softwareFun.addDlgMouseEvent(document.querySelector('.dlg1_aa')) // 拖动条
    },
    buttonNext () {
      const showMsg = msg => {
        this.errorMsg = msg
        setTimeout(() => {
          this.errorMsg = ''
        }, 1000)
      }
      const clearInput = () => {
        this.userInput.pass = ''
      }
      const ifData = (pass) => {
        if (pass === '') {
          showMsg('请输入安全密码')
          return false
        }
        if (pass.length < 6) {
          showMsg('长度不能低于6位')
          return false
        }
        return true
      }
      const pass = this.userInput.pass
      if (ifData(pass)) {
        const result = this.w.softwareApi.app('Login', 'LoginPass', { pass: pass })
        if (!result) {
          showMsg('安全密码错误')
        } else {
          this.w.softwareApi.app('Login', 'ShowMainDlg')
        }
      }
      clearInput()
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
