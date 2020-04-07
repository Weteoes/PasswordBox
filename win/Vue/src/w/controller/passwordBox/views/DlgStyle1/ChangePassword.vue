<template>
  <div class="dlg_form" @keydown="dlgKeyDown">
    <div class="title1">此密码请自行记录,丢失后数据将无法恢复</div>
    <div class="userInputAll">
      <div class="userInputOnly">
        <input class="userInput" v-model="userInput.oldPass" placeholder="请输入旧安全密码" type="password" v-w-focus />
      </div>
      <div class="userInputOnly">
        <input class="userInput" v-model="userInput.newPass0" placeholder="请输入新安全密码" type="password" />
      </div>
      <div class="userInputOnly">
        <input class="userInput" v-model="userInput.newPass1" placeholder="请再次输入新安全密码" type="password" />
      </div>
    </div>
    <div class="errorMsg" style="height: 16px" v-text="errorMsg"></div>
    <div class="userButton">
      <div class="userButtonOnly">
        <div class="only" @click="buttonNextClick">确定</div>
      </div>
    </div>
  </div>
</template>

<style lang="scss" scoped>
.dlg_form > .title {
  font-size: 14px;
  margin-bottom: 3px;
}
.dlg_form > .title1 {
  color: rgb(252, 63, 79);
  font-size: 12px;
  margin-bottom: 10px;
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
        oldPass: '',
        newPass0: '',
        newPass1: ''
      },
      dlgTitle: '修改密码',
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
    dlgKeyDown: function (a) {
      if (a.keyCode === 13) {
        this.buttonNextClick()
      }
    },
    buttonNextClick () {
      const showMsg = msg => {
        this.errorMsg = msg
        setTimeout(() => {
          this.errorMsg = ''
        }, 1000)
      }
      const clearNewInput = (all = true) => {
        if (all) {
          this.userInput.newPass0 = ''
        }
        this.userInput.newPass1 = ''
      }
      const clearOldInput = () => {
        this.userInput.oldPass = ''
      }
      const ifNewData = (pass0, pass1) => {
        if (pass0 === '' || pass1 === '') {
          showMsg('请输入安全密码')
          clearNewInput()
          return false
        }
        if (pass0.length < 6) {
          showMsg('长度不能低于6位')
          clearNewInput()
          return false
        }
        if (pass0 !== pass1) {
          showMsg('密码不一致')
          clearNewInput(false)
          return false
        }
        return true
      }
      const ifOldData = (pass) => {
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
      const oldPass = this.userInput.oldPass
      const newPass0 = this.userInput.newPass0
      const newPass1 = this.userInput.newPass1
      // 判断密码格式
      if (!ifOldData(oldPass)) {
        clearOldInput()
        return
      }
      if (!ifNewData(newPass0, newPass1)) {
        return
      }
      // 密码格式正确，判断旧密码
      const resultOld = this.w.softwareApi.app('ChangePassword', 'LoginPass', { pass: oldPass })
      if (!resultOld) {
        showMsg('旧密码错误')
        return
      }
      // 设置新密码
      const resultNew = this.w.softwareApi.app('ChangePassword', 'ResetAESPassword',
        { oldPass: oldPass, newPass: newPass1 }
      )
      if (!resultNew) {
        showMsg('修改密码出现问题')
        return
      }
      // 修改成功
      this.w.softwareApi.app('ChangePassword', 'ShowMainDlg')
      clearOldInput(true)
      clearNewInput()
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
