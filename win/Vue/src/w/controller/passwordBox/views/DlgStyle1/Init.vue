<template>
  <div class="dlg_form"
       @keydown="dlgKeyDown">
    <div class="title">第一次使用请设置一个安全密码</div>
    <div class="title1">此密码请自行记录,丢失后数据将无法恢复</div>
    <div class="userInputAll">
      <div class="userInputOnly">
        <input class="userInput"
               v-model="userInput.pass0"
               placeholder="请输入安全密码"
               type="password"
               v-w-focus />
      </div>
      <div class="userInputOnly">
        <input class="userInput"
               v-model="userInput.pass1"
               placeholder="请再次输入安全密码"
               type="password" />
      </div>
    </div>
    <div class="errorMsg"
         style="height: 16px"
         v-text="errorMsg"></div>
    <div class="userButton">
      <div class="userButtonOnly">
        <div class="only"
             @click="buttonNextClick">确定</div>
      </div>
    </div>
  </div>
</template>

<style lang="scss" scoped>
.dlg_form > .title {
  height: 20px;
  font-size: 14px;
  margin-bottom: 3px;
}
.dlg_form > .title1 {
  height: 20px;
  color: rgb(252, 63, 79);
  font-size: 12px;
  margin-bottom: 10px;
}
.dlg_form > .errorMsg {
  height: 18px;
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
        pass0: '',
        pass1: ''
      },
      dlgTitle: '设置密码',
      dlgStyle: 'width: 350px', // 需要和readyCEFSize一起修改
      errorMsg: ''
    }
  },
  methods: {
    ready () {
      this.$parent.dlgStyle = this.dlgStyle // 样式
      this.$parent.dlgTitle = this.dlgTitle // 标题
      this.$parent.$parent.readyCEFSize({ w: 350, div: '.dlg1_a' }) // 设置窗口大小
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
      const clearInput = (all = true) => {
        if (all) {
          this.userInput.pass0 = ''
        }
        this.userInput.pass1 = ''
      }
      const ifData = (pass0, pass1) => {
        if (pass0 === '' || pass1 === '') {
          showMsg('请输入安全密码')
          clearInput()
          return false
        }
        if (pass0.length < 6) {
          showMsg('长度不能低于6位')
          clearInput()
          return false
        }
        if (pass0 !== pass1) {
          showMsg('密码不一致')
          clearInput(false)
          return false
        }
        return true
      }
      const pass0 = this.userInput.pass0
      const pass1 = this.userInput.pass1
      if (ifData(pass0, pass1)) {
        const result = this.w.softwareApi.app('Init', 'AesInit', { pass: pass0 })
        if (!result) {
          showMsg('初始化数据库失败')
        } else {
          this.w.softwareApi.app('Init', 'ShowMainDlg')
          clearInput()
        }
      }
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
