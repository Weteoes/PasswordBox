<template>
  <div class="dlg_a dlg_a_">
    <div class="dlg_aa">
      <div class="title">设置密码</div>
      <div class="dlg_aa_menu">
        <div class="dlg_aa_menu_" @click="this.$parent.menuMin" id="menu_min"></div>
        <div class="dlg_aa_menu_" @click="this.$parent.menuExit" id="menu_exit"></div>
      </div>
    </div>
    <div class="dlg_ab">
      <div class="dlg_form">
        <div class="title">第一次使用请设置一个安全密码</div>
        <div class="title1">此密码请自行记录,丢失后数据将无法恢复</div>
        <div class="userInputAll">
          <div class="userInputOnly">
            <input class="userInput" v-model="userInput.pass0" placeholder="请输入安全密码" type="password" />
          </div>
          <div class="userInputOnly">
            <input class="userInput" v-model="userInput.pass1" placeholder="请再次输入安全密码" type="password" />
          </div>
        </div>
        <div class="errorMsg" style="height: 16px" v-text="errorMsg"></div>
        <div class="userButton">
          <div class="userButtonOnly">
            <div class="only" @click="buttonNext" id="next">确定</div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style lang="scss" scoped>
  .dlg_a_ {
    width: 350px;
  }
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
      w: window.Weteoes,
      userInput: {
        pass0: '',
        pass1: ''
      },
      errorMsg: ''
    }
  },
  methods: {
    buttonNext () {
      const showMsg = (msg) => {
        this.errorMsg = msg
        setTimeout(() => {
          this.errorMsg = ''
        }, 1000)
      }
      const ifData = (pass0, pass1) => {
        if (pass0 === '' || pass1 === '') {
          showMsg('请输入安全密码')
          return false
        }
        if (pass0.length < 6) {
          showMsg('长度不能低于6位')
          return false
        }
        if (pass0 !== pass1) {
          showMsg('密码不一致')
          this.userInput.pass1 = ''
          return false
        }
        return true
      }
      const pass0 = this.userInput.pass0
      const pass1 = this.userInput.pass1
      if (ifData(pass0, pass1)) {
        this.w.Basic.Ajax()
      }
    }
  },
  mounted () {
    window.a = this
  }
}
</script>
