<template>
  <footer id="Footer">
    <div class="center">
      <div class="left onlyModule">
        <div class="title">关于</div>
        <div class="info">
          一款实用的密码保管箱。通过不可逆加密模式保护您的账号密码安全，为您的隐私保驾护航。
        </div>
      </div>
      <div class="right onlyModule">
        <div class="title">联系我们</div>
        <div class="info">如有任何意见或建议，可通过一下方式联系到我们</div>
        <div class="info">邮箱：mail@weteoes.cn</div>
      </div>
    </div>
    <div class="more">粤ICP备19082525号</div>
  </footer>
</template>

<style lang="less" scoped>
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
      padding-left: 35px;
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
</style>
