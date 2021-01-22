<template>
  <footer id="Footer">
    <!-- 返回顶部 -->
    <a-back-top />
    <!-- Footer -->
    <div class="center">
      <div class="left onlyModule">
        <div class="title">关于</div>
        <div class="info">
          一款实用的密码保管箱。通过不可逆加密模式保护您的账号密码安全，为您的隐私保驾护航。
        </div>
      </div>
      <div class="right onlyModule">
        <div class="title">联系我们</div>
        <div class="info">如有任何意见或建议，可通过以下方式联系到我们</div>
        <div class="info">
          邮箱：
          <a href="mailto:mail@weteoes.cn" target="_blank"> mail@weteoes.cn </a>
        </div>
        <div class="info">
          GitHub：
          <a href="https://github.com/Weteoes/PasswordBox" target="_blank">
            Weteoes/PasswordBox
          </a>
        </div>
      </div>
    </div>
    <div class="more">
      <a href="https://beian.miit.gov.cn" target="_blank">粤ICP备19082525号</a>
    </div>
  </footer>
</template>

<style lang="less" scoped>
.Media_Browser({
  footer {
    @minWidth: 1200px;
    @padding: 30px;

    & {
      background: #f5f5f6;
      color: #808080;
      padding: @padding 0 10px;
    }
    > .center {
      & {
        .minWidth();
      }
      > .left {
        .inline();
        padding-left: @padding;
        width: 500px;
      }

      > .right {
        .inline();
        padding-left: 33px;
      }

      > .onlyModule {
        > .title {
          font-size: 20px;
          padding-bottom: 10px;
        }

        > .info {
          font-size: 15px;
        }
      }

      .inline () {
        display: inline-block;
        vertical-align: top;
      }
    }

    > .more {
      margin-top: 30px;
      text-align: center;
      font-size: 14px;
    }

    .minWidth() {
      width: @minWidth;
      margin: 0 auto;
    }
  }
});

.Media_Phone({
  footer {
    @padding: 10px;

    & {
      background: #f5f5f6;
      color: #808080;
      padding: @padding 0 10px;
    }
    > .center {
      > .onlyModule {
        & {
          width: 90vw;
          margin: 0 auto 20px;
        }
        > .title {
          font-size: 20px;
          padding-bottom: 10px;
        }

        > .info {
          font-size: 15px;
        }
      }
    }

    > .more {
      margin-top: 30px;
      text-align: center;
      font-size: 14px;
    }
  }
});
</style>
