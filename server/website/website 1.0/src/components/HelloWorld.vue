<template>
  <div class="hello">
    <h1>{{ msg }}</h1>
    <h1>{{ a }}</h1>
    <p>
      For a guide and recipes on how to configure / customize this project,<br />
      check out the
      <a href="https://cli.vuejs.org" target="_blank" rel="noopener"
        >vue-cli documentation</a
      >.
    </p>
    <h3>Installed CLI Plugins</h3>
    <el-button>默认按钮</el-button>
  </div>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'vue-property-decorator'
import { State } from 'vuex-class'

@Component
export default class HelloWorld extends Vue {
  @State('debug')
  stateDebug: undefined;

  @Prop()
  private msg!: string;

  @Prop({ default: 2 })
  private a: number | undefined;

  mounted () {
    (window as any).a = this
    this.$message({ type: 'success', message: '1' })
    console.log(this.$store.state.debug, this.stateDebug)
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped lang="scss">
h3 {
  margin: 40px 0 0;
}
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
a {
  color: #42b983;
}
</style>
