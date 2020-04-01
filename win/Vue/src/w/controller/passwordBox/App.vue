<template>
    <div>
        <router-view/>
    </div>
</template>

<style lang="scss">
    $padding_left: 15px;
    .dlg_a {
        border: 1px solid #000;
        min-width: 300px;
        min-height: 200px;
        display: flex;
        flex-direction: column;
    }
    .dlg_aa {
        display: flex;
        width: 100%;
        min-height: 30px;
        background: #31acff;
    }
    .dlg_aa > .title {
        flex: 1;
        padding: 0 $padding_left;
        line-height: 30px;
        font-size: 15px;
    }
    .dlg_aa_menu {
        display: flex;
        min-width: 30px;
    }
    .dlg_aa_menu_ {
        width: 30px;
        line-height: 30px;
        text-align: center;
    }

    .dlg_aa_menu > #menu_exit:hover{
        background: #f04c46;
    }

    .dlg_aa_menu > #menu_exit::before {
        content: "X";
    }

    .dlg_aa_menu > #menu_min:hover{
        background: #189df5;
    }

    .dlg_aa_menu > #menu_min::before {
        content: "";
        display: block;
        margin: 14px auto;
        width: 12px;
        height: 2px;
        background: #000;
    }
    .dlg_ab {
        flex: 1;
        width: auto;
        min-height: 30px;
        padding: $padding_left;
    }
</style>

<script>
export default {
  methods: {
    ready_ () {
      this.readySoftwareApi()
    },
    menuMin () {
      alert('Min')
    },
    menuExit () {
      alert('Exit')
    },
    readySoftwareApi () {
      if (typeof window.Weteoes === 'undefined') {
        window.Weteoes = {}
      }
      window.Weteoes.softwareApi = {

      }
    }
  },

  created () {
    this.ready_()
    window.WeteoesBrowser.Dlg.Size(100, 300)
  }
}
</script>
