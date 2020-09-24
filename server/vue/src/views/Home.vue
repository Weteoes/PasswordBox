<template>
  <div id="Home">
    <nav>
      <el-menu
        :default-active="navNowSelect"
        class="el-menu-demo"
        mode="horizontal"
        @select="navSelectHandle"
      >
        <el-menu-item>
          <div class="logo">
            <img src="@/assets/logo.png" />
            <span>密码保管箱</span>
          </div>
        </el-menu-item>
        <el-menu-item index="Download">下载</el-menu-item>
        <el-menu-item index="GitHub">GitHub
          <a ref="GitHub" href="https://github.com/Weteoes/PasswordBox" target="_blank"></a>
        </el-menu-item>
      </el-menu>
    </nav>
    <div class="step">
      <!-- Step0 -->
      <div class="onlyStep">
        <div class="png"><img src="@/assets/step0.png"/></div>
        <div class="data onlyStepData">
          <div class="data">
            <div class="title">本地工作模式</div>
            <div class="text">本地工作，数据将通过AES256加密后保存本地，数据更加安全。</div>
          </div>
        </div>
      </div>
      <!-- Step1 -->
      <div class="onlyStep">
        <div class="data onlyStepData">
          <div class="data">
            <div class="title">AES256加密模式</div>
            <div class="text">AES256加密后，只有在正确输入密码的情况下，数据才会被程序正确解读，如果密码丢失，则数据将无法恢复。</div>
          </div>
        </div>
        <div class="png"><img src="@/assets/step1.png"/></div>
      </div>
      <!-- Step2 -->
      <div class="onlyStep">
        <div class="png"><img src="@/assets/step2.png"/></div>
        <div class="data onlyStepData">
          <div class="data">
            <div class="title">界面简洁无广告</div>
            <div class="text">界面简洁，但功能不减，无多余内容</div>
          </div>
        </div>
      </div>
      <!-- Step End -->
    </div>
  </div>
</template>

<script lang="ts">
import Vue from 'vue'
import { Component } from 'vue-property-decorator'

@Component
export default class Home extends Vue {
  navNowSelect = ''; // 当前Nav选择

  navSelectHandle (key: any, keyPath: any) {
    if (key === null) return
    switch (key) {
      case 'GitHub': {
        (this.$refs.GitHub as HTMLAnchorElement).click()
        this.navNowSelect = '' // 清空Nav选择
        break
      }
    }
    this.log(key, keyPath)
  }

  log (...data: any) {
    console.log(...data)
  }

  mounted () {
    // this.$message('')
    (window as any).a = this
  }
}
</script>

<style lang="scss" scoped>
$bodyWidth: 1200px;

#Home {
  min-width: $bodyWidth;
}

nav {
  $navHeight: 61px; // element-ui（don't modify）
  .logo {
    cursor: default;
    img {
      height: $navHeight - 25px
    }
    span {
      padding-left: 10px;
      color: #000
    }
  }
  a {
    text-decoration: none;
  }
}
.step {
  > .onlyStep {
    display: flex;
    width: $bodyWidth;
    margin: 50px auto 100px auto;
    padding: 20px 0;

    > .png {
      flex: 2;
      text-align: center;
    }
    > .data {
      flex: 1;
    }
  }
}

.onlyStepData {
  display: flex;
  flex-direction: column;
  justify-content: center;

  > .data {
    width: 300px;
    height: auto;
    margin: 20px auto;
    %textMargin {
      margin: 10px auto;
    }
    > .title {
      font-size: 26px;
      text-align: center;
      @extend %textMargin;
    }
    > .text {
      font-size: 15px;
      @extend %textMargin;
    }
  }
}
</style>
