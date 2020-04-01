<template>
  <div class="dlg_a" style="width:300px;height:200px;">
    <div class="dlg_aa">
      <div class="title">设置密码</div>
      <div class="dlg_aa_menu">
        <div class="dlg_aa_menu_" id="menu_min"></div>
        <div class="dlg_aa_menu_" id="menu_exit"></div>
      </div>
    </div>
    <div class="dlg_ab">
      <div class="dlg_form">
        <div class="title">第一次使用请设置一个安全密码</div>
        <div class="title1">此密码请自行记录,丢失后数据将无法恢复</div>
      </div>
    </div>
  </div>
</template>

<style scoped>
  .dlg_form > .title {
    color: rgb(252, 63, 79);
    font-size: 14px;
  }
  .dlg_form > .title1 {
    color: rgb(252, 63, 79);
    font-size: 12px;
  }
</style>

<script>
export default {
  data () {
    return {
      a: 1
    }
  }
}
</script>
