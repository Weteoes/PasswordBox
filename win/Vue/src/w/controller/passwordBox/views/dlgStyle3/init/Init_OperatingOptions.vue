<template>
  <div class="dlg">
    <div class="title">软件将按照不同的工作模式进行工作</div>
    <div class="title1">切换工作模式将清空数据</div>
    <div class="data">
      <div class="onlyData">
        <el-select class="dataSelect"
                   v-model="optionsNow"
                   placeholder="请选择">
          <el-option v-for="item in options"
                     :key="item.value"
                     :label="item.label"
                     :value="item.value">
          </el-option>
        </el-select>
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
  margin: 50px auto;
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
      optionsNow: '',
      options: [
        { value: 'local', label: '本地工作模式' },
        { value: 'server', label: '统一认证登录' }
      ]
    }
  },
  methods: {
    ready () {
      this.readyData()
    },
    nextButtonClick () {
      if (this.optionsNow === '') {
        this.showMessageBox('请选择工作模式', 'error')
        return
      }
      this.synchronize()
      this.$parent.stepActive++
    },
    readyData () {
      this.optionsNow = this.$parent.$data.data.optionsNow
    },
    synchronize () {
      this.$parent.$data.data.optionsNow = this.optionsNow
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
